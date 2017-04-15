Pod::Spec.new do |spec|
  spec.name         = 'SceneGraph'
  spec.version      = '1.0.0'
  spec.license      = { :type => 'BSD' }
  spec.homepage     = 'https://github.com/mutexre/SceneGraph'
  spec.authors      = { 'Alexander Obuschenko' => 'alexander.obuschenko@gmail.com' }
  spec.summary      = 'SceneGraph'
  spec.source       = { :git => 'https://github.com/mutexre/SceneGraph.git', :tag => 'v1.0.0' }
  spec.module_name  = 'SceneGraph'
  spec.ios.deployment_target = '8.0'
  spec.osx.deployment_target = '10.10'
  spec.source_files = 'SceneGraph/*.{hpp,cpp}', 'SceneGraph/Misc/*.{hpp,cpp}', 'SceneGraph/Material/*.{hpp,cpp}', 'SceneGraph/Mesh/*.{hpp,cpp}', 'SceneGraph/Image/*.{hpp,cpp}', 'SceneGraph/Import/*.{hpp,cpp}', 'SceneGraph/Surface/*.{hpp,cpp}', 'SceneGraph/Settings/*.{hpp,cpp}'
  spec.dependency 'CoreGraphics', 'CoreText'
end
